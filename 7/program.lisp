(ql:quickload :cl-utilities)

(declaim (optimize (speed 2)))

(defun read-input (file)
  (mapcar #'parse-integer
		  (cl-utilities:split-sequence #\, (car (uiop:read-file-lines file)))))

(defun sum-iota (n)
  (/ (* n (+ n 1)) 2))

(defun solve (file)
  (let* ((input (read-input file))
	 (maxi (reduce #'max input))
	 (mini (reduce #'min input)))
    (loop for x from mini to maxi
	  minimize (reduce #'+ (loop for y in input
				     collect (sum-iota (abs (- y x))))))))
