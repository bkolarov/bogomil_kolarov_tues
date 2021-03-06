require 'csv'

file_name = ARGV[0]
parameter = ARGV[1]
arr = []

CSV.foreach(file_name, "r") do |row|
	if row[2].to_f > parameter.to_f
		arr << row
	end
end


arr = arr.sort_by{|x| x[2].to_i}
arr = arr.reverse()
file_name = file_name.split('.csv')

CSV.open("#{file_name[0]}_result3.csv", "wb") do |f|
	arr.each do |x|
		f << x
	end
end
