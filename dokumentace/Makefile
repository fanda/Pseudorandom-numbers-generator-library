manual: dokumentace.tex
	latex dokumentace.tex
	bibtex dokumentace.aux
	latex dokumentace.tex
	latex dokumentace.tex
	dvips dokumentace.dvi
	ps2pdf -sPAPERSIZE=a4 dokumentace.ps

clean:
	rm -f *.bbl *.dvi *.aux *.blg *.log *.ps
