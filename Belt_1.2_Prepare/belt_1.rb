require 'csv'

file_name = ARGV[0]
arr = []

CSV.foreach(file_name, "r") do |row|
	if row[4] =~ /#{ARGV[1]}/
		arr << row
	end
end

arr = arr.sort_by{ |x| x[2].to_i }

file_name = file_name.split('.csv')

CSV.open("#{file_name[0]}_result.csv", "wb") do |f|
	arr.each do |x|
		f << x
	end
end
