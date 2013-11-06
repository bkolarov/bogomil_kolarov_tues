require 'csv'
require 'date'

file_name = ARGV[0]
date = Date.parse(ARGV[1])

arr = []

CSV.foreach(file_name, "r") do |row|
	if Date.parse(row[1]) < date
		arr << row
	end
end

arr = arr.sort_by { |x| x[2].to_i }
arr = arr.reverse()

file_name = file_name.split('.csv')

CSV.open("#{file_name[0]}_result4.csv", "wb") do |f|
	arr.each do |x|
		f << x
	end
end
