#!/bin/sh

set -e

# Exception dict: standard
# Word: ภูมิใจ ภูมิลำเนา ภาคภูมิ ภูมิศาสตร์ ภูมิทัศน์
# Output: Thai

srcdir=${srcdir-.}

echo "Testing 'ภูมิใจ'"
../thpronun -d../../data/except.dic -t ภูมิใจ | grep "พูม-จัย" 2>/dev/null

echo "Testing 'ภูมิลำเนา'"
../thpronun -d../../data/except.dic -t ภูมิลำเนา | grep "พูม-ลัม-เนา" 2>/dev/null

echo "Testing 'ภาคภูมิ'"
../thpronun -d../../data/except.dic -t ภาคภูมิ | grep "พาก-พูม" 2>/dev/null

echo "Testing 'ภูมิศาสตร์'"
../thpronun -d../../data/except.dic -t ภูมิศาสตร์ | grep "พู-มิ-สาด" 2>/dev/null

echo "Testing 'ภูมิทัศน์'"
../thpronun -d../../data/except.dic -t ภูมิทัศน์ | grep "พู-มิ-ทัด" 2>/dev/null
