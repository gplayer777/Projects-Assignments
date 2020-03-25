#lang racket
(require rackunit/text-ui)
(require rackunit)


(struct const (val) #:transparent)
(struct op (symb l r) #:transparent)
(struct variable () #:transparent)
(struct ∂ (f) #:transparent)


(define (der f)
  (match f
    [(const n)   (const 0)]
    [(variable)  (const 1)]
    [(op '+ f g) (op '+ (der f) (der g))]
    [(op '* f g) (op '+ (op '* (der f) g)
                        (op '* f (der g)))]))

(define (eval e v)
  (match e
    [(const n) n]
    [(variable) v] 
    [(∂ f) (eval (der f) v)]
    [(op '+ l r) (+ (eval l v) (eval r v))]
    [(op '* l r) (* (eval l v) (eval r v))]))


(define f (op '+ (op '* (const 2) (variable)) (∂(op '+ (op '* (variable) (variable))
                 (variable)))))

(define abstr-rep-tests
    (test-suite
     "test "

    
     (test-case
      "test1"
      (let ((f (op '+ (const 2) (variable))))
        
        (check-equal? (eval f 5) 7 )))
     
     (test-case
      "test2"
      (let  ((f (op '+ (op '* (const 2) (variable)) (∂(op '+ (op '* (variable) (variable))
                 (variable))))))
        (check-equal? (eval f 3) 13)))
     ))

(run-tests abstr-rep-tests)





