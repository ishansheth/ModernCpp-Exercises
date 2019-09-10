
;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
;;(invert-face 'default)

(load-theme 'misterioso)
(global-linum-mode t)

(package-initialize)


(ido-mode 1)

(setq ido-separator "\n")

(global-set-key [M-left] 'windmove-left)          ; move to left window
(global-set-key [M-right] 'windmove-right)        ; move to right window
(global-set-key [M-up] 'windmove-up)              ; move to upper window
(global-set-key [M-down] 'windmove-down)          ; move to lower window

(setq tab-always-indent 'complete)

(add-to-list 'load-path "/home/ishan/emacs-neotree")
(require 'neotree)
(global-set-key [f8] 'neotree-toggle)
(display-time-mode 1)

(require 'package)
;; Any add to list for package-archives (to add marmalade or melpa) goes here
(add-to-list 'package-archives 
    '("MELPA" .
      "http://melpa.milkbox.net/packages/"))
(package-initialize)

(require 'auto-complete)
(require 'auto-complete-config)
(ac-config-default)
(require 'yasnippet)
(yas-global-mode 1)

(defun my:ac-c-headers-init()
	(required 'auto-complete-c-headers)
	(add-to-list 'ac-sources 'ac-source-c-headers)
	(add-to-list 'achead:include-directories '"/usr/include")
	(add-to-list 'achead:include-directories '"/usr/include/c++/7")
	(add-to-list 'achead:include-directories '"/usr/local/include")
	(add-to-list 'achead:include-directories '"/usr/include/x86_64-linux-gnu/c++/7")
)
(setq x-select-enable-clipboard t)
(setq interprogram-paste-function 'x-cut-buffer-or-selection-value)

;;(add-hook 'c++-mode-hook 'my:ac-c-headers-init)
;;(add-hook 'c-mode-hook 'my:ac-c-headers-init)

;;(semantic-mode 1)
;;(defun my:add-semantic-to-autocomplete()
;;	(add-to-list 'ac-sources 'ac-source-semantic)
;;)

;;(add-hook 'c-mode-common-hook 'my:add-semantic-to-autocomplete)

;;(global-ede-mode 1)
;;(global-semantic-idle-scheduler-mode 1)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(custom-safe-themes
   (quote
    ("a0feb1322de9e26a4d209d1cfa236deaf64662bb604fa513cca6a057ddf0ef64" default)))
 '(package-selected-packages
   (quote
    (yasnippet auto-complete-c-headers nlinum alect-themes cmake-project all-the-icons-ivy all-the-icons-dired 2048-game xkcd))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
(cua-mode t)

