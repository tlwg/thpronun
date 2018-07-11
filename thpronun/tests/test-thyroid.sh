#!/bin/sh

set -e

# Exception dict: standard
# Word: ไทร ไทรบุรี ไทรอยด์ รีไทร์
# Output: Thai

srcdir=${srcdir-.}

echo "Testing 'ไทร'"
../thpronun -d../../data/except.dic -t ไทร | grep "ซัย" 2>/dev/null

echo "Testing 'ไทรบุรี'"
../thpronun -d../../data/except.dic -t ไทรบุรี | grep "ซัย-บุ-รี" 2>/dev/null

echo "Testing 'ไทรอยด์'"
../thpronun -d../../data/except.dic -t ไทรอยด์ | grep "ทัย-รอย" 2>/dev/null

echo "Testing 'รีไทร์'"
../thpronun -d../../data/except.dic -t รีไทร์ | grep "รี-ทัย" 2>/dev/null
