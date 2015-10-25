n, m = gets.split.map(&:to_i)
a = gets.split

hash = Hash.new(0)
ans = {}

a.each do | e |
  hash[e] += 1
end

hash.select! { | key, value | value > n/2 }

if hash.size == 1
  puts hash.keys
else
  puts "?"
end

