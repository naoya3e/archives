n, m = gets.split.map(&:to_i)

angleShort = (n%12)*30 + m*0.5
angleLong = m * 6

ans = (angleShort - angleLong).abs
puts (ans < 180)? ans: 360-ans

