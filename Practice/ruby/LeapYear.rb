# coding: utf-8

print "閏年かどうかを判定します : "
year = gets.to_i

if (year%4 == 0 && year%100 != 0) || year%400 == 0
  puts "#{year}年は閏年です."
else
  puts "#{year}年は閏年ではありません."
end
