require 'csv'

fileName = ARGV[0]
result = ARGV[1]

sortedArray = Array.new
outputArray = Array.new

CSV.foreach(fileName) do |row|
	sortedArray << row
end

sortedArray = sortedArray.sort_by { |a| a[6].to_i }

if ARGV[2] == nil
	max = 5
else
	max = ARGV[2].to_i
end

if max > CSV.readlines(fileName).size.to_i
	max = CSV.readlines(fileName).size.to_i
end
count = 0

sortedArray.each do |element|

	if element[1].to_i > result.to_i
		outputArray << element
		count = count + 1
		if count == max
			break
		end
	end

end

outputArray = outputArray.sort_by { |a| a[3].to_i }

CSV.open("top.csv", "wb") do |row|
	outputArray.each do |element|
		row << element
	end
end