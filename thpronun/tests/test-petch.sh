#!/bin/sh

set -e

# Exception dict: standard
# Word: สรเพชญ สรรเพชญ สรรเพชญ์ สรรเพ็ชญ สรรเพ็ชญ์ เพชฌฆาต เพชฉลูกรรม
#   เพชร เพชรบุรี เพชรบูรณ์ เพชรา
# Output: Thai

srcdir=${srcdir-.}

echo "Testing 'สรเพชญ'"
../thpronun -d../../data/except.dic -t สรเพชญ | grep "สฺระ-เพ็ด" 2>/dev/null

echo "Testing 'สรรเพชญ'"
../thpronun -d../../data/except.dic -t สรรเพชญ | grep "สัน-เพ็ด" 2>/dev/null

echo "Testing 'สรรเพชญ์'"
../thpronun -d../../data/except.dic -t สรรเพชญ์ | grep "สัน-เพ็ด" 2>/dev/null

echo "Testing 'สรรเพ็ชญ'"
../thpronun -d../../data/except.dic -t สรรเพ็ชญ | grep "สัน-เพ็ด" 2>/dev/null

echo "Testing 'สรรเพ็ชญ์'"
../thpronun -d../../data/except.dic -t สรรเพ็ชญ์ | grep "สัน-เพ็ด" 2>/dev/null

echo "Testing 'เพชฌฆาต'"
../thpronun -d../../data/except.dic -t เพชฌฆาต | grep "เพ็ด-ชะ-คาด" 2>/dev/null

echo "Testing 'เพชฉลูกรรม'"
../thpronun -d../../data/except.dic -t เพชฉลูกรรม | grep "เพ็ด-ฉะ-หฺลู-กัม" 2>/dev/null

echo "Testing 'เพชร'"
../thpronun -d../../data/except.dic -t เพชร | grep "เพ็ด" 2>/dev/null

echo "Testing 'เพชรบุรี'"
../thpronun -d../../data/except.dic -t เพชรบุรี | grep "เพ็ด-บุ-รี" 2>/dev/null

echo "Testing 'เพชรบูรณ์'"
../thpronun -d../../data/except.dic -t เพชรบูรณ์ | grep "เพ็ด-ชะ-บูน" 2>/dev/null

echo "Testing 'เพชรา'"
../thpronun -d../../data/except.dic -n -t เพชรา | grep "เพ็ด-ชะ-รา" 2>/dev/null
