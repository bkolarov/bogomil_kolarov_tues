import sqlite3 as lite

def getColumnsAndTypesOfTable(tableName, con):
	result = ''
	records = executeQuery('PRAGMA table_info(' + tableName + ')', con).fetchall()
	result += records[0][1]
	records.pop(0)
	for record in records:
		result += ', '
		result += record[1]

	return result	
	
def executeQuery(query, con):
	print query
	cursor = con.cursor()
	result = cursor.execute(query)
	con.commit()
	
	return result

con = lite.connect('SUBD_exam.db')
print getColumnsAndTypesOfTable('Article', con)

con.close()
