data = gets.split.map(&:to_i)

takahashi = data[1]/data[0].to_f
aoki = data[3]/data[2].to_f

if takahashi > aoki
  puts "TAKAHASHI"
elsif aoki > takahashi
  puts "AOKI"
else
  puts "DRAW"
end

