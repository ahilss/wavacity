#!/bin/sh
set -o errexit
echo ";; Recreating wavacity.pot using .h, .cpp and .mm files"
for path in ../modules/mod-script* ../modules/mod-nyq* ../include ../src ; do find $path -name \*.h -o -name \*.cpp -o -name \*.mm ; done | LANG=c sort | \
sed -E 's/\.\.\///g' |\
xargs xgettext \
--default-domain=wavacity \
--directory=.. \
--keyword=_ --keyword=XO --keyword=XC:1,2c --keyword=XXO --keyword=XXC:1,2c --keyword=XP:1,2 --keyword=XPC:1,2,4c \
--add-comments=" i18n" \
--add-location=file  \
--copyright-holder='Wavacity Team' \
--package-name="wavacity" \
--package-version='3.0.1' \
--msgid-bugs-address="wavacity-translation@lists.sourceforge.net" \
--add-location=file -L C -o wavacity.pot 
echo ";; Adding nyquist files to wavacity.pot"
for path in ../plug-ins ; do find $path -name \*.ny -not -name rms.ny; done | LANG=c sort | \
sed -E 's/\.\.\///g' |\
xargs xgettext \
--default-domain=wavacity \
--directory=.. \
--keyword=_ --keyword=_C:1,2c --keyword=ngettext:1,2 --keyword=ngettextc:1,2,4c \
--add-comments=" i18n" \
--add-location=file  \
--copyright-holder='Wavacity Team' \
--package-name="wavacity" \
--package-version='3.0.1' \
--msgid-bugs-address="wavacity-translation@lists.sourceforge.net" \
--add-location=file -L Lisp -j -o wavacity.pot 
if test "${WAVACITY_ONLY_POT:-}" = 'y'; then
    return 0
fi
echo ";; Updating the .po files - Updating Project-Id-Version"
for i in *.po; do
    sed -i '/^"Project-Id-Version:/c\"Project-Id-Version: wavacity 3.0.1\\n"' $i
done
echo ";; Updating the .po files"
sed 's/.*/echo "msgmerge --lang=& &.po wavacity.pot -o &.po";\
msgmerge --lang=& &.po wavacity.pot -o &.po;/g' LINGUAS | bash
echo ";; Removing '#~|' (which confuse Windows version of msgcat)"
for i in *.po; do
    sed -i '/^#~|/d' $i
done
echo ""
echo ";;Translation updated"
echo ""
head -n 11 wavacity.pot | tail -n 3
wc -l wavacity.pot
