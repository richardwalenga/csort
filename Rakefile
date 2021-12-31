#!/usr/bin/env ruby
# -*- ruby -*-

require 'rake/clean'

object_files = FileList['*.c'].collect {|x| x[0...-1] + 'o'}
CLEAN << object_files.select {|x| File.file? x}
CLEAN << "csort" if File.file? "csort"

rule '.o' => ['.c'] do |t|
    sh "cc #{t.source} -c -o #{t.name}"
end

file "csort" => object_files do |t|
    sh "cc -o #{t.name} #{t.prerequisites.join(' ')} -lm"
end

task :rebuild do
    Rake::Task[:clean].invoke
    Rake::Task["csort"].invoke
end

task :default => :rebuild