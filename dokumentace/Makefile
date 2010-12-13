manual: dokumentace.tex
	pdflatex --shell-escape dokumentace.tex
	bibtex dokumentace.aux
	pdflatex --shell-escape dokumentace.tex
	pdflatex --shell-escape dokumentace.tex
#	dvips dokumentace.dvi
#	ps2pdf -sPAPERSIZE=a4 dokumentace.ps

clean:
	rm -f *.bbl *.dvi *.aux *.blg *.log *.ps
