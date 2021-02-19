#!/usr/bin/python3

import io
import sys
import pyparsing

try:
  if len(sys.argv) < 2:
    print("c_stripcomments.py error: pass the path to a file as the second argument.")
  else:
    comments = pyparsing.nestedExpr("/*", "*/").suppress()
    with io.open(sys.argv[1], 'r', encoding='utf8') as fd:
      print(comments.transformString(fd.read()))
except:
  print("c_stripcomments.py error:", sys.exc_info())
