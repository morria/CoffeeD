#!/usr/bin/perl
#
# @author Andrew Morrison <asm@etsy.com>
# 

use POSIX qw(floor);

$coffee = `curl -s http://10.252.1.146:8080/`;
$cups = floor($coffee/270);


if(0 >= $cups) {
    print "Sorry, there is no coffee left.\n";
}
elsif(1 == $cups) {
    print "Hurry, there is only 1 cup of coffee left.\n";
}
elsif(10 < $cups) {
    print "Someone is pouring a cup right now. Try again.\n";
}
else {
    print "There are $cups cups of coffee left.\n";
}
