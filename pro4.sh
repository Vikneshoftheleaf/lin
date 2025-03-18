echo "Argument1:$1"
echo "Argument2:$2"
echo "Argument3:$3"
echo "Argument4:$4"
echo "Argument5:$5"
echo "Argument6:$6"
if [ $# -eq 6 ]; then
echo "Program received with sufficient argument"
p=$1 # Store the first argument as the pattern
shift # Shift to start processing the remaining arguments
for a in "$@"; do
echo "Pattern found in $a"
grep "$p" "$a" # Search for the pattern in each file
done
fi
