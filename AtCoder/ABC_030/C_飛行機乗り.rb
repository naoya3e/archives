now = 0
count = 0

n, m = gets.split.map(&:to_i)
x, y = gets.split.map(&:to_i)

a = gets.split.map(&:to_i)
b = gets.split.map(&:to_i)

loop do
  a = a.drop_while { | ai | ai < now }
  break if a.empty?
  now = a.first + x

  b = b.drop_while { | bi | bi < now }
  break if b.empty?
  now = b.first + y

  count += 1
end

puts count
