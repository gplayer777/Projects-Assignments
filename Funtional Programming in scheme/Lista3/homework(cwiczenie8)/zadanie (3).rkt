#lang racket
(require rackunit/text-ui)
(require rackunit)

(define (split list)
    (cons (take list (floor (/ (length list) 2))) (drop list (floor (/ (length list) 2))) ))

(define (merge list1 list2)
    (cond ((null? list1) list2)
          ((null? list2) list1)
          ((< (car list1) (car list2))
             (cons (car list1) (merge (cdr list1) list2)))
             (else (cons (car list2) (merge list1 (cdr list2))))))
(define (mergesort list)
    (cond ((null? list) list)
          ((null? (cdr list))
              list)
             (else (merge (mergesort (car (split list))) (mergesort (cdr (split list)))))))
(define mergesort-tests
    (test-suite
     "test split"

     (check-equal? (list? (merge '(1 2) '(2 3))) true) 
     (test-case
      "test1"
      (let ((list1 (split '(1 2 3 4))))
        (check-equal? (car list1) '(1 2))
        (check-equal? (cdr list1) '(3 4))))
     (test-case
      "test2"
      (let ((list1 '(1 2))
            (list2 '(5 8)))
        (check-equal? (merge list1 list2) '(1 2 5 8))))
     (test-case
      "test3"
      (let ((list1 '(1 2 5 6)))
        (check-equal? (mergesort list1) '(1 2 5 6))))
     ))

(run-tests mergesort-tests)
