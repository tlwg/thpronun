#!/bin/sh

set -e

# Exception dict: standard
# Word: ราชคฤห์ สนานคฤห์ รติคฤห์ คฤหัสถ์
# Output: Thai

srcdir=${srcdir-.}

echo "Testing 'ราชคฤห์'"
../thpronun -d../../data/except.dic -t ราชคฤห์ | grep "ราด-ชะ-คฺรึ" 2>/dev/null

echo "Testing 'สนานคฤห์'"
../thpronun -d../../data/except.dic -t สนานคฤห์ | grep "สะ-หฺนาน-คฺรึ" 2>/dev/null

echo "Testing 'รติคฤห์'"
../thpronun -d../../data/except.dic -t รติคฤห์ | grep "ระ-ติ-คฺรึ" 2>/dev/null

echo "Testing 'คฤหัสถ์'"
../thpronun -d../../data/except.dic -t คฤหัสถ์ | grep "คะ-รึ-หัด" 2>/dev/null
