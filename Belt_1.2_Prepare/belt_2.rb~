require 'csv'

file_name = ARGV[0]
h = {}
arr = []
sum = 0

CSV.foreach(file_name, "r") do |row|
	row1 = row[4].split(' ')[0]
	h[row1] = h[row1].to_i + row[2].to_i
end

h.each do |line|
	arr << line
end

arr = arr.sort_by{|x| x[1].to_i}

file_name = file_name.split('.csv')
p file_name

CSV.open("#{file_name[0]}_result2.csv", "wb") do |f|
	arr.each do |x|
		f << x
	end
end
