## Development utilities for c-stringcompare
##
## Usage:
## 		make <target> [<arg>=<value> ...]
##
## Targets:
## 		help:		Show this help message.
## 		docs:		Generate doxygen documentation.

.PHONY: help docs

help: makefile
	@sed -n "s/^##//p" $<

docs:
	doxygen .doxygenconfig