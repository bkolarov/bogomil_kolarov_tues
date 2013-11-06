require 'csv'

file_name = ARGV[0]










CSV.open("#{file_name[0]}_result2.csv", "wb") do |f|
	arr.each do |x|
		f << x
	end
end
