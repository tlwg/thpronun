#!/bin/sh

set -e

# Exception dict: standard
# Word: เชาวน์ เวทางค์ เสนางค์
# Output: Thai

srcdir=${srcdir-.}

echo "Testing 'มีเชาวน์'"
../thpronun -d../../data/except.dic -t มีเชาวน์ | grep "มี-เชา" 2>/dev/null

echo "Testing 'เวทางค์'"
!(../thpronun -d../../data/except.dic -t เวทางค์ | grep "วะ-เทา" 2>/dev/null)
../thpronun -d../../data/except.dic -t เวทางค์ | grep "เว-ทาง" 2>/dev/null

echo "Testing 'เสนางค์'"
!(../thpronun -d../../data/except.dic -t เสนางค์ | grep "สะ-เหฺนา" 2>/dev/null)
../thpronun -d../../data/except.dic -t เสนางค์ | grep "เส-นาง" 2>/dev/null
