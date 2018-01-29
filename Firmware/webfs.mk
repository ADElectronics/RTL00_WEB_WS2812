include userset.mk
include $(SDK_PATH)paths.mk

all:

	@mkdir -p $(BIN_DIR)
	./tools/WEBFS22.exe -h "*.htm, *.html, *.cgi, *.xml, *.bin, *.js, *.txt, *.wav" -z "mdbini.bin, *.inc, *.ini, snmp.bib, *.ovl" ./WEBFiles $(BIN_DIR) WEBFiles.bin

clean:
