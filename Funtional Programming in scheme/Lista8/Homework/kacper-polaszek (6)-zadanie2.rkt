#lang racket
(require rackunit/text-ui)
(require rackunit)


(module my-module-1 racket
  (provide (all-defined-out))
  (require rackunit/text-ui)
(require rackunit)

  ;; definicja wyrażeń z let-wyrażeniami i if-wyrażeniami

(struct variable (x)         #:transparent)
(struct const    (val)       #:transparent)
(struct op       (symb l r)  #:transparent)
(struct let-expr (x e1 e2)   #:transparent)
(struct if-expr  (b t e)     #:transparent)



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
    [_                  false]))

;; definicja instrukcji w języku WHILE


(struct skip      ()       #:transparent) ; skip
(struct comp      (s1 s2)  #:transparent) ; s1; s2
(struct assign    (x e)    #:transparent) ; x := e
(struct while     (b s)    #:transparent) ; while (b) s
(struct if-stm    (b t e)  #:transparent) ; if (b) t else e
(struct var-block (x e s)  #:transparent) ; var x := e in s



(define (stm? e)
  (match e
    [(skip) true]
    [(comp s1 s2)   (and (stm? s1) (stm? s2))]
    [(assign x e)   (and (symbol? x) (expr? e))]
    [(while b s)    (and (expr? b) (stm? s))]
    [(if-stm b t e) (and (expr? b) (stm? t) (stm? e))]
    [_ false]))
  
;; wyszukiwanie wartości dla klucza na liście asocjacyjnej
;; dwuelementowych list

(define (lookup x xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (mcar (car xs)) x) (mcar (mcdr (car xs)))]
    [else (lookup x (cdr xs))]))

;; aktualizacja środowiska dla danej zmiennej (koniecznie już
;; istniejącej w środowisku!)

(define (update x v xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (mcar (car xs)) x)
     (set-mcar! (mcdr (car xs)) v)]
    [else
      (update x v (cdr xs))])
  xs)

;; kilka operatorów do wykorzystania w interpreterze

(define (op-to-proc x)
  
  (lookup x  (list ( mcons '+ (mcons + null))
              ( mcons '* (mcons * null))
             ( mcons '- (mcons - null))
              ( mcons '/ (mcons / null))
              ( mcons '% (mcons modulo null))
             ( mcons '> (mcons > null))
             ( mcons '>= (mcons >= null))
              ( mcons '< (mcons < null))
              ( mcons '<= (mcons <= null))
             ( mcons '= (mcons = null))
             ( mcons '!= (mcons (lambda (x y) (not (= x y))) null))
               ( mcons '&& (mcons (lambda (x y) (and x y)) null))
               ( mcons '|| (mcons (lambda (x y) (or x y)) null))
              )))

;; interfejs do obsługi środowisk




(define (env-empty) null)
(define env-lookup lookup)
(define (env-add x v env) (cons (mcons x (mcons v '())) env))
(define env-update update)
(define env-discard cdr)
(define (env-from-assoc-list xs) xs)


;; ewaluacja wyrażeń ze środowiskiem

(define (eval e env)
  (match e
    [(const n) n]
    [(op s l r) ((op-to-proc s) (eval l env)
                                (eval r env))]
    [(let-expr x e1 e2)
     (let ((v1 (eval e1 env)))
       (eval e2 (env-add x v1 env)))]
    [(variable x) (env-lookup x env)]
    [(if-expr b t e) (if (eval b env)
                         (eval t env)
                         (eval e env))]))

;; interpretacja programów w języku WHILE, gdzie środowisko m to stan
;; pamięci. Interpreter to procedura, która dostaje program i początkowy
;; stan pamięci, a której wynikiem jest końcowy stan pamięci. Pamięć to
;; aktualne środowisko zawierające wartości zmiennych

(define (interp p m)
  (match p
    [(skip) m]
    [(comp s1 s2) (interp s2 (interp s1 m))]
    [(assign x e)
     (env-update x (eval e m) m)]
    [(while b s)
     (if (eval b m)
         (interp p (interp s m))
         m)]
    [(var-block x e s)
     (env-discard
       (interp s (env-add x (eval e m) m)))]
    [(if-stm b t e) (if (eval b m)
                        (interp t m)
                        (interp e m))]))

;; silnia zmiennej i

(define fact-in-WHILE
  (var-block 'x (const 0)                                           ; var x := 0 in
     (comp (assign 'x (const 1))                                    ;   x := 1
     (comp (while (op '> (variable 'i) (const 0))                   ;   while (i > 0)
              (comp (assign 'x (op '* (variable 'x) (variable 'i))) ;     x := x * i
                    (assign 'i (op '- (variable 'i) (const 1)))))   ;     i := i - 1
           (assign 'i (variable 'x))))))                            ;   i := x

(define (factorial n)
  (env-lookup 'i (interp fact-in-WHILE
                         (env-from-assoc-list (list (mcons 'i (mcons n null)))))))



  (define (factorial-native n)
 (cond ((< n 0) #f)
         ((<= n 1) 1)
         (else (* n (factorial (- n 1))))))

;; najmniejsza liczba pierwsza nie mniejsza niż i

(define find-prime-in-WHILE
 (var-block 'c (variable 'i)                                         ; var c := i in
 (var-block 'continue (const true)                                   ; var continue := true in
 (comp
  (while (variable 'continue)                                        ; while (continue)
   (var-block 'is-prime (const true)                                 ;   var is-prime := true in
   (var-block 'x (const 2)                                           ;   var x := 2 in
    (comp
     (while (op '&& (variable 'is-prime)                             ;   while (is-prime &&
                    (op '< (variable 'x) (variable 'c)))             ;            x < c)
        (comp (if-stm (op '= (op '% (variable 'c) (variable 'x))     ;     if (c % x =
                             (const 0))                              ;                 0)
                      (assign 'is-prime (const false))               ;       is-prime := false
                      (skip))                                        ;     else skip
              (assign 'x (op '+ (variable 'x) (const 1)))))          ;     x := x + 1 
     (if-stm (variable 'is-prime)                                    ;   if (is-prime)
             (assign 'continue (const false))                        ;     continue := false
             (comp (assign 'continue (const true))                   ;   else continue := true
                   (assign 'c (op '+ (variable 'c) (const 1))))))))) ;        c := c + 1
  (assign 'i (variable 'c))))))                                      ; i := c

(define (find-prime-using-WHILE n)
  (env-lookup 'i (interp find-prime-in-WHILE
                         (env-from-assoc-list (list (mcons 'i (mcons n null)) (mcons 'is-prime  (mcons #t null)))))))          

;; porownajmy wydajnosc!

;; ten sam algorytm do wyszukiwania liczby pierwszej nie mniejszej niż n
;; zapisany funkcyjnie jest dosc brzydki, ale odpowiada temu zapisanemu w WHILE

(define (find-prime-native n)
  (define (is-prime c isp x)
    (if (and isp (< x c))
      (if (= (modulo c x) 0)
          (is-prime c false (+ x 1))
          (is-prime c isp   (+ x 1)))
      isp))
  (if (is-prime n true 2)
      n
      (find-prime-native (+ n 1))))

;; testujemy, żeby dowiedzieć się, jak dużo wydajności tracimy przez
;; uruchamianie programu w naszym interpreterze

(define (test)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance)))

(define (test-performance)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply find-prime-using-WHILE (list 1111111)))
       ((r2 cpu2 real2 gc2) (time-apply find-prime-using-WHILE (list 11)))
       ((r3 cpu3 real3 gc3) (time-apply find-prime-using-WHILE (list 1111)))
       
       ((r4 cpu4 real4 gc4) (time-apply factorial (list 11111)))
       ((r5 cpu5 real5 gc5) (time-apply factorial (list 6)))
       ((r6 cpu6 real6 gc6) (time-apply factorial (list 1)))




       )

    
    (begin
      (display "MODIFIED: WHILE  time (1111111) (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")

      (display "MODIFIED: WHILE  time (11) (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n")

      (display "MODIFIED: WHILE  time (1111) (cpu, real, gc): ")
      (display cpu3)  (display ", ")
      (display real3) (display ", ")
      (display gc3)   (display "\n")

      (display "MODIFIED: factorial  time (1111) (cpu, real, gc): ")
      (display cpu4)  (display ", ")
      (display real4) (display ", ")
      (display gc4)   (display "\n")

      (display "MODIFIED: factorial  time (6) (cpu, real, gc): ")
      (display cpu5)  (display ", ")
      (display real5) (display ", ")
      (display gc5)   (display "\n")

      (display "MODIFIED: factorial  time (1) (cpu, real, gc): ")
      (display cpu6)  (display ", ")
      (display real6) (display ", ")
      (display gc6)   (display "\n")

)))
)

(module my-module-2 racket
  (provide (all-defined-out)) 


  ;; definicja wyrażeń z let-wyrażeniami i if-wyrażeniami

(struct variable (x)         #:transparent)
(struct const    (val)       #:transparent)
(struct op       (symb l r)  #:transparent)
(struct let-expr (x e1 e2)   #:transparent)
(struct if-expr  (b t e)     #:transparent)

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
    [_                  false]))

;; definicja instrukcji w języku WHILE

(struct skip      ()       #:transparent) ; skip
(struct comp      (s1 s2)  #:transparent) ; s1; s2
(struct assign    (x e)    #:transparent) ; x := e
(struct while     (b s)    #:transparent) ; while (b) s
(struct if-stm    (b t e)  #:transparent) ; if (b) t else e
(struct var-block (x e s)  #:transparent) ; var x := e in s

(define (stm? e)
  (match e
    [(skip) true]
    [(comp s1 s2)   (and (stm? s1) (stm? s2))]
    [(assign x e)   (and (symbol? x) (expr? e))]
    [(while b s)    (and (expr? b) (stm? s))]
    [(if-stm b t e) (and (expr? b) (stm? t) (stm? e))]
    [_ false]))
  
;; wyszukiwanie wartości dla klucza na liście asocjacyjnej
;; dwuelementowych list

(define (lookup x xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (caar xs) x) (cadar xs)]
    [else (lookup x (cdr xs))]))

;; aktualizacja środowiska dla danej zmiennej (koniecznie już
;; istniejącej w środowisku!)

(define (update x v xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (caar xs) x)
     (cons (list (caar xs) v) (cdr xs))]
    [else
     (cons (car xs) (update x v (cdr xs)))]))

;; kilka operatorów do wykorzystania w interpreterze

(define (op-to-proc x)
  (lookup x `((+ ,+)
              (* ,*)
              (- ,-)
              (/ ,/)
              (%, modulo)
              (> ,>)
              (>= ,>=)
              (< ,<)
              (<= ,<=)
              (= ,=)
              (!= ,(lambda (x y) (not (= x y)))) 
              (&& ,(lambda (x y) (and x y)))
              (|| ,(lambda (x y) (or x y)))
              )))

;; interfejs do obsługi środowisk

(define (env-empty) null)
(define env-lookup lookup)
(define (env-add x v env) (cons (list x v) env))
(define env-update update)
(define env-discard cdr)
(define (env-from-assoc-list xs) xs)

;; ewaluacja wyrażeń ze środowiskiem

(define (eval e env)
  (match e
    [(const n) n]
    [(op s l r) ((op-to-proc s) (eval l env)
                                (eval r env))]
    [(let-expr x e1 e2)
     (let ((v1 (eval e1 env)))
       (eval e2 (env-add x v1 env)))]
    [(variable x) (env-lookup x env)]
    [(if-expr b t e) (if (eval b env)
                         (eval t env)
                         (eval e env))]))

;; interpretacja programów w języku WHILE, gdzie środowisko m to stan
;; pamięci. Interpreter to procedura, która dostaje program i początkowy
;; stan pamięci, a której wynikiem jest końcowy stan pamięci. Pamięć to
;; aktualne środowisko zawierające wartości zmiennych

(define (interp p m)
  (match p
    [(skip) m]
    [(comp s1 s2) (interp s2 (interp s1 m))]
    [(assign x e)
     (env-update x (eval e m) m)]
    [(while b s)
     (if (eval b m)
         (interp p (interp s m))
         m)]
    [(var-block x e s)
     (env-discard
       (interp s (env-add x (eval e m) m)))]
    [(if-stm b t e) (if (eval b m)
                        (interp t m)
                        (interp e m))]))

;; silnia zmiennej i

(define fact-in-WHILE
  (var-block 'x (const 0)                                           ; var x := 0 in
     (comp (assign 'x (const 1))                                    ;   x := 1
     (comp (while (op '> (variable 'i) (const 0))                   ;   while (i > 0)
              (comp (assign 'x (op '* (variable 'x) (variable 'i))) ;     x := x * i
                    (assign 'i (op '- (variable 'i) (const 1)))))   ;     i := i - 1
           (assign 'i (variable 'x))))))                            ;   i := x

(define (factorial n)
  (env-lookup 'i (interp fact-in-WHILE
                         (env-from-assoc-list `((i ,n))))))


  (define (factorial-native n)
 (cond ((< n 0) #f)
         ((<= n 1) 1)
         (else (* n (factorial (- n 1))))))

;; najmniejsza liczba pierwsza nie mniejsza niż i

(define find-prime-in-WHILE
 (var-block 'c (variable 'i)                                         ; var c := i in
 (var-block 'continue (const true)                                   ; var continue := true in
 (comp
  (while (variable 'continue)                                        ; while (continue)
   (var-block 'is-prime (const true)                                 ;   var is-prime := true in
   (var-block 'x (const 2)                                           ;   var x := 2 in
    (comp
     (while (op '&& (variable 'is-prime)                             ;   while (is-prime &&
                    (op '< (variable 'x) (variable 'c)))             ;            x < c)
        (comp (if-stm (op '= (op '% (variable 'c) (variable 'x))     ;     if (c % x =
                             (const 0))                              ;                 0)
                      (assign 'is-prime (const false))               ;       is-prime := false
                      (skip))                                        ;     else skip
              (assign 'x (op '+ (variable 'x) (const 1)))))          ;     x := x + 1 
     (if-stm (variable 'is-prime)                                    ;   if (is-prime)
             (assign 'continue (const false))                        ;     continue := false
             (comp (assign 'continue (const true))                   ;   else continue := true
                   (assign 'c (op '+ (variable 'c) (const 1))))))))) ;        c := c + 1
  (assign 'i (variable 'c))))))                                      ; i := c

(define (find-prime-using-WHILE n)
  (env-lookup 'i (interp find-prime-in-WHILE
                         (env-from-assoc-list `((i ,n) (is-prime ,true))))))          

;; porownajmy wydajnosc!

;; ten sam algorytm do wyszukiwania liczby pierwszej nie mniejszej niż n
;; zapisany funkcyjnie jest dosc brzydki, ale odpowiada temu zapisanemu w WHILE

(define (find-prime-native n)
  (define (is-prime c isp x)
    (if (and isp (< x c))
      (if (= (modulo c x) 0)
          (is-prime c false (+ x 1))
          (is-prime c isp   (+ x 1)))
      isp))
  (if (is-prime n true 2)
      n
      (find-prime-native (+ n 1))))

;; testujemy, żeby dowiedzieć się, jak dużo wydajności tracimy przez
;; uruchamianie programu w naszym interpreterze

(define (test)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance)))

(define (test-performance)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply find-prime-using-WHILE (list 1111111)))
       ((r2 cpu2 real2 gc2) (time-apply find-prime-using-WHILE (list 11)))
       ((r3 cpu3 real3 gc3) (time-apply find-prime-using-WHILE (list 1111)))
       
       ((r4 cpu4 real4 gc4) (time-apply factorial (list 11111)))
       ((r5 cpu5 real5 gc5) (time-apply factorial (list 6)))
       ((r6 cpu6 real6 gc6) (time-apply factorial (list 1)))

       
       ((r7 cpu7 real7 gc7) (time-apply find-prime-native (list 1111111)))
       ((r8 cpu8 real8 gc8) (time-apply find-prime-native (list 11)))
       ((r9 cpu9 real9 gc9) (time-apply find-prime-native (list 1111)))


       ((r10 cpu10 real10 gc10) (time-apply factorial-native (list 11111)))
       ((r11 cpu11 real11 gc11) (time-apply factorial-native (list 6)))
       ((r12 cpu12 real12 gc12) (time-apply factorial-native (list 1)))

       
       )
    (begin
      (display "ORIGINAL: WHILE  time (1111111) (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")

      (display "ORIGINAL: WHILE  time (11) (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n")

      (display "ORIGINAL: WHILE  time (1111) (cpu, real, gc): ")
      (display cpu3)  (display ", ")
      (display real3) (display ", ")
      (display gc3)   (display "\n")

      (display "ORIGINAL: factorial  time (11111) (cpu, real, gc): ")
      (display cpu4)  (display ", ")
      (display real4) (display ", ")
      (display gc4)   (display "\n")

      (display "ORIGINAL: factorial  time (6) (cpu, real, gc): ")
      (display cpu5)  (display ", ")
      (display real5) (display ", ")
      (display gc5)   (display "\n")

      (display "ORIGINAL: factorial  time (1) (cpu, real, gc): ")
      (display cpu6)  (display ", ")
      (display real6) (display ", ")
      (display gc6)   (display "\n")
      
      (display "native time prime (1111111) (cpu, real, gc): ")
      (display cpu7)  (display ", ")
      (display real7) (display ", ")
      (display gc7)   (display "\n")


      (display "native time prime (11) (cpu, real, gc): ")
      (display cpu8)  (display ", ")
      (display real8) (display ", ")
      (display gc8)   (display "\n")

      (display "native time prime (1111) (cpu, real, gc): ")
      (display cpu9)  (display ", ")
      (display real9) (display ", ")
      (display gc9)   (display "\n")


      (display "native time factorial (11111) (cpu, real, gc): ")
      (display cpu10)  (display ", ")
      (display real10) (display ", ")
      (display gc10)   (display "\n")
   
      (display "native time factorial (6) (cpu, real, gc): ")
      (display cpu11)  (display ", ")
      (display real11) (display ", ")
      (display gc11)   (display "\n")


      (display "native time factorial (1) (cpu, real, gc): ")
      (display cpu12)  (display ", ")
      (display real12) (display ", ")
      (display gc12)   (display "\n")
      

  ))

       
  
))


(require (prefix-in mod1: 'my-module-1))
(require (prefix-in mod2: 'my-module-2))

(define modified-interp
   (mod1:test)
   )
(define original-interp
   (mod2:test)
   )

;; WNIOSKI: dla programów w języku while podanych w przykładzie zamiana reprezentacji srodkowiska z niemutowalnych list składających się z dwuelementowych 
;; niemutowalnych list na reprezentacje w postaci list mutowalnych list nie powoduje zadnego wzrostu wydajnosci, niezaleznie od danych wejsciowych
;; „Czy istnieje chociaz jeden program, dla którego optymalizacja stanowczo skraca czas wykonania?”. - w przypadku wykonanych przeze mnie testow
;; odpowiedz brzmi nie



