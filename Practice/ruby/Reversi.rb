#!/usr/bin/env ruby
# coding: utf-8

#
#  [color]  1:white     -1:black
#  [player] 1:human      0:cpu
#
#  [status] true:continue   false:break
#

class Reversi
  attr_reader   :status
  attr_accessor :player

  SQUARE = 8

  def initialize
    @color  = 1
    @passed = 0
    @player = 1
    @status = 1
    @field = Array.new(SQUARE+2){Array.new(SQUARE+2, 0)}
    @field[4][4], @field[5][5] =  1,  1
    @field[4][5], @field[5][4] = -1, -1
  end

  def showBoard
    puts "   1 2 3 4 5 6 7 8"

    1.upto SQUARE do | y |
      print " #{y}"
      1.upto SQUARE do | x |
        case @field[y][x]
          when  0
            print "\e[32m"
            print " □"
            print "\e[0m"
          when  1
            print " ○"
          when -1
            print " ●"
        end
      end
      puts
    end
  end

  def putStone(x, y)
    @field[y][x] = @color
  end

  def checkField(x, y)
    3.times do | moveY |
      3.times do | moveX |
        if @field[y+moveY-1][x+moveX-1] == -1 * @color
        end
      end
    end
    return true
  end

  def checkPass
    1.upto(SQUARE) do | y |
      1.upto(SQUARE) do | x |
        next if @field[y][x] != 0
        # 周辺探索
      end
    end
  end

  def human
    @status = false if @passed >= 2

    if checkPass
      puts "○  パス"
      return
    end

    loop do
      print "座標を指定してください (x,y) : "
      x, y = gets.split(/,/).map(&:to_i)

      # 入力された座標が足りないかどうか
      if x.nil? || y.nil?
        puts "ERROR: 座標は x,y のように入力してください."
        redo
      end

      # 入力された座標が領域外であるかどうか
      if x < 1 || x > 8 || y < 1 || y > 8
        puts "ERROR: 指定した座標は領域外です."
        redo
      end

      # 入力された座標で石の反転を行えるかどうか
      unless checkField(x, y)
        puts "ERROR: 指定した座標に石は置けません."
        redo
      end

      # 正常に座標が入力されたら入力フェーズを終了する
      break
    end

    putStone(x, y)
  end

  def cpu
  end
end

print "\e[1m"
puts "Welcome to the Reversi game."
print "\e[0m"
puts "This reversi is human vs. cpu."
puts

go = Reversi.new

loop do
  go.showBoard
  go.human

  break unless go.status

  go.player += -1
end

