echo "enter your choice"
echo "1. whoami"
echo "2. free"
echo "3. pwd"
echo "4. ls"
echo "5. ls -d"
echo "6. ls -l"
echo "7. ls-R"
echo "8. date"
echo "9. cal"
echo "10. df"
echo "11. Exit"
while true
do
echo "Enter your choice:"
read ch
case $ch in
1) whoami;;
2) free;;
3) pwd;;
4) ls;;
5) ls -d;;
6) ls -l;;
7) ls -R;;
8) date;;
9) cal;;
10) df;;
11) break;;
*) echo "Invalid choice, please try again."
esac
done
