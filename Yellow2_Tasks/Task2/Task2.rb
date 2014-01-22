require 'csv'

fileName = ARGV[0]

statsArray = Array.new
topArray = Array.new

if(ARGV[1] == nil)
	rows = 5
else 
	rows = ARGV[1].to_i
end 

if CSV.read(fileName).length.to_i < 5
	row = CSV.read(fileName).length
end



CSV.foreach(fileName) do |row|
	statsArray << row
end

statsArray = statsArray.sort_by { |e| [e[2].to_i, e[0].to_i] }

statsArray = statsArray.reverse

count = 0
statsArray.each do |element|
	topArray << element
	count = count + 1
	break if(count == rows) 
end

topArray = topArray.reverse

CSV.open("top.csv", "wb") do |row|
	topArray.each do |element|
		row << element

	end
end