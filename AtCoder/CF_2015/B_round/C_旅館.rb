n, m = gets.split.map(&:to_i)
a = gets.split.map(&:to_i).sort
b = gets.split.map(&:to_i).sort

while bi = b.pop
  ai = a.pop
  if ai == nil || ai < bi
    puts "NO"
    exit
  end
end

puts "YES"

