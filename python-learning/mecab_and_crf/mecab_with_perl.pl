#! /usr/bin/perl -w

use strict;
#use warnings;
use Text::MeCab;

my $m = Text::MeCab->new();
my $s = "日本語の形態素解析が難しい。";
my $n = $m->parse($s);

while ($n = $n->next) {
  print "surface: ".$n->surface."\n";  # 表層
  print "feature: ".$n->feature."\n";  # 現在の瀕死
  print "cost: ".$n->cost."\n\n";      # その形態素までのコスト
}
