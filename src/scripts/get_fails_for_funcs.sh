FILE='test.log'
TMP_FILE=script_fails_tmp.tmp

RED='\033[1;31m'
GR='\033[1;32m'
NC='\033[0m'

echo "Success tests:"
grep ":\w*[0-9]*:.: " test.log -o | grep "s21_\w*_test" -o | sort | uniq > ${TMP_FILE}
while IFS="" read -r p || [ -n "$p" ]
do
    PASSES=$(grep "$p:[a-zA-Z_0-9]*:.:\s*Passed" ${FILE} -c)
    TOTAL=$(grep "$p[^\n]*" ${FILE} -c)
    if [ "$TOTAL" == "$PASSES" ]; then
        printf "$p \t: %5s/%-5s\t ${GR}Success${NC}\n" "${PASSES}" "${TOTAL}"
    else
        printf "$p \t: %5s/%-5s\t ${RED}Fail${NC}\n" "${PASSES}" "${TOTAL}"
    fi
done < ${TMP_FILE}
rm ${TMP_FILE}

if [ "$(grep "Failures: 0" test.log)" == "" ]
then
    echo -e "${RED}-------------------------------------------------${NC}"
    echo -e "${RED}FAIL${NC}: $(grep "Checks" test.log)"
    echo -e "${RED}-------------------------------------------------${NC}"
    echo -e "More info in test.log"

else
    echo -e "${GR}-------------------------------------------------${NC}"
    echo -e "${GR}SUCCESS${NC}: $(grep "Checks" test.log)"
    echo -e "${GR}-------------------------------------------------${NC}"
fi
