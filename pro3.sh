#!/bin/bash
if [ "$#" -lt 3 ]; then
echo "Usage: sh $0 subject body <user1> <user2> <user3> <user4> <user5>..."
exit 1
fi
sub=$1
con=$2
shift
shift
for user in "$@"
do
echo "$con" | mail -s "$sub" "$user"
echo "The mail was sent at $(date) to $user"
done