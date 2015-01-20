(in-package :cl-user)
(defpackage cmacro
  (:use :cl :anaphora)
  (:import-from :cmacro.macroexpand
                :macroexpand-string)
  (:import-from :cmacro.printer
                :print-ast)
  (:import-from :cmacro.parser
                :slurp-file)
  (:export :main))
(in-package :cmacro)

(defun quit ()
  (sb-ext:exit :code -1))

(setf *debugger-hook* #'(lambda (c h)
                          (declare (ignore h))
                          (format t "~A~&" c)
                          (quit)))

(defparameter +help+
  "Usage: cmc [file|expr]+

  Process all files/expressions as a single file in the order in which they appear in the command line.
  Expressions begin with a newilne character, anything else is treated as a file name.
  Output is sent to standard output; for any useful purpose a redirect/pipe should be employed.")

(defun main (args)
  (let ((files-exprs (cdr args)))
    (unless files-exprs
      (format t "~A~%" +help+)
      (error 'cmacro.error:no-input-files))
    (labels ((is-expr? (e) (or (= (length e) 0) (char= (elt e 0) #\newline)))
             (handle-elem (e) (if (is-expr? e) e (slurp-file (parse-namestring e))))
             (process-string (s) (print-ast (macroexpand-string s)))
             (combine-all (l) (apply #'concatenate 'string l))
             (read-all (l) (map 'list #'handle-elem l)))
      (write-string (process-string (combine-all (read-all files-exprs)))))
    (terpri)))
