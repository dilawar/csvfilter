#!/bin/bash - 
#===============================================================================
#
#          FILE: test.sh
# 
#         USAGE: ./test.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Dilawar Singh (), dilawars@ncbs.res.in
#  ORGANIZATION: NCBS Bangalore
#       CREATED: 04/05/2017 04:36:02 PM
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error
./csvfilter -i ./text.dat -p 'time sw\d\.x0y6\[\d\]\.N'

