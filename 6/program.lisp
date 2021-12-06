(ql:quickload :cl-utilities)

(defun read-input (file)
  (mapcar #'parse-integer
		  (cl-utilities:split-sequence #\, (car (uiop:read-file-lines file)))))

(defparameter *M*
  '((0 1 0 0 0 0 0 0 0)
    (0 0 1 0 0 0 0 0 0)
    (0 0 0 1 0 0 0 0 0)
    (0 0 0 0 1 0 0 0 0)
    (0 0 0 0 0 1 0 0 0)
    (0 0 0 0 0 0 1 0 0)
    (1 0 0 0 0 0 0 1 0)
    (0 0 0 0 0 0 0 0 1)
    (1 0 0 0 0 0 0 0 0)))

(defparameter *N* 256)

(defun count-pop (list)
  (loop for i from 0 below 9
	collect (loop for n in list count (equal n i))))

(defun dot-product (v1 v2)
  (loop for a in v1
	for b in v2
	sum (* a b)))

(defun matrix-*-vector (m v)
  (mapcar #'(lambda (row)
	 (dot-product v row))
	  m))

(defun solve ()
  (let ((vec (count-pop (read-input "input.txt")))
	(new_vec '()))
    (loop for i from 0 below *N*
	  do (setf new_vec (matrix-*-vector *M* vec))
	     (setf vec new_vec))
    (reduce #'+ new_vec)))
