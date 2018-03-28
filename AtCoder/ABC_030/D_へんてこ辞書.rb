N, a = gets.split.map(&:to_i)
k = gets.to_i
b = gets.split.map(&:to_i)

b.unshift(0)

hist = []

k.times do
  hist << a = b[a]
  p hist
end

puts a
