#!/usr/bin/perl
#  install_ispring.pl.pl
#  ISpring
#
#  Created by kimbom on 2017. 11. 10...
#  Copyright 2017 kimbom. All rights reserved.
#
use strict;
use warnings;
use feature qw(say);
my $zip="/tmp/ISpring.zip";
system "wget https://github.com/springkim/ISpring_repo/archive/master.zip -O $zip";
if(-d "/tmp/ISpring"){
	system "rm -r /tmp/ISpring";
}
system "unzip $zip -d /tmp/ISpring";
if(-d "ispring"){
	system "rm -r ispring";
}
system "cp -r /tmp/ISpring/ISpring_repo-master/ispring ./ispring";

