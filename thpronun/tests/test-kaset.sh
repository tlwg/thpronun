#!/bin/sh

# Exception dict: เกษตร, สหกรณ์
# Word: การเกษตรและสหกรณ์การเกษตร
# Output: Grouped JSON

srcdir=${srcdir-.}

echo "Generating dictionary"
cat > test-kaset.lst << EOF
เกษตร	k_a_1@-5,s_Et1@5
สหกรณ์	s_a_1@1,h_a_1@2,k_Cn0@6
EOF
../../dict/gen-lookup-dict test-kaset.lst test-kaset.dic

echo "Testing thpronun with the exception dict"
../thpronun -dtest-kaset.dic -g -t การเกษตรและสหกรณ์การเกษตร
