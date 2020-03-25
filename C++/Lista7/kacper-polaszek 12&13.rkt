#lang racket
(require rackunit/text-ui)
(require rackunit)

;; definicja wyrażeń

(struct variable     (x)        #:transparent)
(struct const        (val)      #:transparent)
(struct op           (symb l r) #:transparent)
(struct let-expr     (x e1 e2)  #:transparent)
(struct if-expr      (b t e)    #:transparent)
(struct cons-expr    (l r)      #:transparent)
(struct car-expr     (p)        #:transparent)
(struct cdr-expr     (p)        #:transparent)
(struct pair?-expr   (p)        #:transparent)
(struct null-expr    ()         #:transparent)
(struct null?-expr   (e)        #:transparent)
(struct symbol-expr  (v)        #:transparent)
(struct symbol?-expr (e)        #:transparent)
(struct lambda-expr  (xs b)     #:transparent)
(struct app-expr     (f es)     #:transparent)
(struct apply-expr   (f e)      #:transparent)


(define (expr? e)
  (match e
    [(variable s)       (symbol? s)]
    [(const n)          (or (number? n)
                            (boolean? n))]
    [(op s l r)         (and (member s '(+ *))
                             (expr? l)
                             (expr? r))]
    [(let-expr x e1 e2) (and (symbol? x)
                             (expr? e1)
                             (expr? e2))]
    [(if-expr b t e)    (andmap expr? (list b t e))]
    [(cons-expr l r)    (andmap expr? (list l r))]
    [(car-expr p)       (expr? p)]
    [(cdr-expr p)       (expr? p)]
    [(pair?-expr p)     (expr? p)]
    [(null-expr)        true]
    [(null?-expr p)     (expr? p)]
    [(symbol-expr v)    (symbol? v)]
    [(symbol?-expr p)   (expr? p)]
    [(lambda-expr xs b) (and (list? xs)
                             (andmap symbol? xs)
                             (expr? b)
                             (not (check-duplicates xs)))]
    [(app-expr f es)    (and (expr? f)
                             (list? es)
                             (andmap expr? es))]
    [(apply-expr f e)   (and (expr? f)
                             (expr? e))]
    [_                  false]))

;; wartości zwracane przez interpreter

(struct val-symbol (s)   #:transparent)
(struct closure (x b e))




(define (my-value? v)
  (or (number? v)
      (boolean? v)
      (and (pair? v)
           (my-value? (car v))
           (my-value? (cdr v)))
      ; null-a reprezentujemy symbolem (a nie racketowym
      ; nullem) bez wyraźnej przyczyny
      (and (symbol? v) (eq? v 'null))
      (and ((val-symbol? v) (symbol? (val-symbol-s v))))
      (and (closure? v) (symbol? (closure-x v))
                        (expr? (closure-b v))
                        (env? (closure-e v)))))
      

;; wyszukiwanie wartości dla klucza na liście asocjacyjnej
;; dwuelementowych list

(define (lookup x xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (caar xs) x) (cadar xs)]
    [else (lookup x (cdr xs))]))

;; kilka operatorów do wykorzystania w interpreterze

(define (op-to-proc x)
  (lookup x `(
              (+ ,+)
              (* ,*)
              (- ,-)
              (/ ,/)
              (> ,>)
              (>= ,>=)
              (< ,<)
              (<= ,<=)
              (= ,=)
              (eq? ,(lambda (x y) (eq? (val-symbol-s x)
                                       (val-symbol-s y))))
              
              )))

;; interfejs do obsługi środowisk

(define (env-empty) null)
(define env-lookup lookup)
(define (env-add x v env) (cons (list x v) env))

(define (env? e)
  (and (list? e)
       (andmap (lambda (xs) (and (list? e)
                                 (= (length e) 2)
                                 (symbol? (first e)))))))

;; interpretacja wyrażeń
;; (cons-expr (const 1) (cons-expr (const 2) (null-expr)))
(define (eval e env)
  (match e
    [(const n) n]
    [(op s l r)
     ((op-to-proc s) (eval l env)
                     (eval r env))]
    [(let-expr x e1 e2)
     (let ((v1 (eval e1 env)))
       (eval e2 (env-add x v1 env)))]
    [(variable x) (env-lookup x env)]
    [(if-expr b t e) (if (eval b env)
                         (eval t env)
                         (eval e env))]
    [(cons-expr l r)
     (let ((vl (eval l env))
           (vr (eval r env)))
       (cons vl vr))]
    [(car-expr p)      (car (eval p env))]
    [(cdr-expr p)      (cdr (eval p env))]
    [(pair?-expr p)    (pair? (eval p env))]
    [(null-expr)       'null]
    [(null?-expr e)    (eq? (eval e env) 'null)]
    [(symbol-expr v)   (val-symbol v)]
    [(lambda-expr xs b) (closure xs b env)]
    [(app-expr f es)    (let ((vf (eval f env)))  ;;
                             
                         (match vf
                           [(closure xs b c-env)

                            (define (helper xss ess c-envs)
                              (if (null? xss)
                                  c-envs
                                  (helper (cdr xss) (cdr ess) (cons (list (car xss) (car ess)) c-envs) )))

                            (if (= (length xs) (length es))
                                (eval b (helper xs es c-env))
                                (error "the number of arguments doesnt match the number of values"))
                            
                            ]
                           [_ (error "application: not a function :(")]))]
    [(apply-expr f es)


     
     (define (convertToRacketList es)
       (define xs (eval es null))
       (define (toList xs)
         (if(eq? xs 'null)
             null
             (cons (car xs) (toList (cdr xs)))))
       (toList xs))
     
       
       


     (define (helper es)   ;; tlumaczymy na nasz jezyk
             (if (eq? (cdr es) null)
                 (const (car es))
                (op f (helper (cdr es)) (const (car es)))))
     

     (define rev-es
                  (reverse (convertToRacketList es)))                            ;; musimy odwrocic liste argumentow zeby ewaluacja zgadzala sie dla przypadku gdy funkcja to dzielenie
     
     (eval (helper rev-es) env)


     ]
    
    ))


;; (cons-expr (const 1) (cons-expr (const 2) (cons-expr (const 3) (null-expr))))



(define basic-test1
  
     (app-expr (lambda-expr '(x y)
     
              (op '+ (op '* (variable 'x) (variable 'y)) (const 10))) ;;spodziewany wynik: 16
               '(3 2) ))

(define basic-test2
  (apply-expr '/ (cons-expr (const 1) (cons-expr (const 2) (cons-expr (const 3) (null-expr)))))) ;; spodziewany wynik 1/6

(define basic-test3
  (apply-expr '+ (cons-expr (const 1) (null-expr)))) ;; spodziewany  wynik 1

(define basic-test4
  (apply-expr '/ (cons-expr (const 2) (cons-expr (const 4) (null-expr)))))  ;; spodziewany wynik 1/2

(define random-expr-test1
  
     (app-expr (lambda-expr '(x y)
     
              (op '* (op '* (variable 'x) (variable 'y)) (apply-expr '/ (cons-expr (const 1) (cons-expr (const 2) (cons-expr (const 9) (null-expr)))))))   ;; spodziewany wynik: 1/3
               '(3 2) ))

(define random-expr-test2
  
     (app-expr (lambda-expr '(x y)
     
              (op '* (op '* (variable 'x) (variable 'y)) (apply-expr '* (cons-expr (const 4) (cons-expr (const 8) (cons-expr (const 7) (null-expr))))))) ;; spodziewany wynik: 1344
               '(3 2) ))






;;;;;;;;;;; te testy do uruchomienia samodzielnie 
(define wrong-expr-test1
  
     (app-expr (lambda-expr '(x y z)
     
              (op '* (op '* (variable 'x) (variable 'y)) (apply-expr '/ (cons-expr (const 1) (cons-expr (const 2) (cons-expr (const 9) (null-expr))))))) ;; spodziewany wynik:   (error "the number of arguments doesnt match the number of values")))
               '(3 2) ))

(define wrong-expr-test2
  
     (app-expr (lambda-expr '(x)
     
              (op '* (op '* (variable 'x) (variable 'y)) (apply-expr '/ (cons-expr (const 1) (cons-expr (const 2) (cons-expr (const 9) (null-expr))))))) ;; spodziewany wynik:   (error "the number of arguments doesnt match the number of values")))
               '(3 2 3) ))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (run e)
  (eval e (env-empty)))


(define interp-tests
  (test-suite
   "Podstawowy test funkcji i aplikacji "
   (check-equal? (= (run basic-test1) 16) true
                 "Funkcja dziala prawidlowo")
   (check-equal? (= (run basic-test2) (apply / '(1 2 3))) true
                 "Funkcja dziala prawidlowo")
   (check-equal? (= (run basic-test3) (apply + '(1))) true
                 "Funkcja dziala prawidlowo")
   (check-equal? (= (run basic-test4) (apply / '(2 4))) true
                 "Funkcja dziala prawidlowo")
   

   (test-case
    "test przykladowego wyrazenia 1"
    (let ((r (run random-expr-test1)))
      (check-equal? r (/ 1 3)
      ))

   (test-case
    "tekst przykladowego wyrazenia 2"
    (let ((r (run random-expr-test2)))
      (check-equal? r 1344)
      ))
)))



(run-tests interp-tests)










