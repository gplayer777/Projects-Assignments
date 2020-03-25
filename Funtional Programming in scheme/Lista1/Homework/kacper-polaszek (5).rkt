#lang racket

(define (cube x) (* x x x))

(define (abs x)
   (if (< x 0)
    (- x)
    x))

(define (dist x y) (abs (- x y)))

(define (cube-root x)
   (define (improve guess)
    (/ (+ (/ x (* guess guess)) (* guess 2)) 3))
   (define (good-enough? g)
    (< (dist x (cube g)) 0.0001))
   (define (iter guess)
    (if (good-enough? guess)
     guess
     (iter (improve guess))))
   (iter 1.0))

;; przyklady testowe
;; (cube-root 8) (cube-root -8) (cube-root -0.125) (cube-root 0.125) (cube-root 64)
;;
