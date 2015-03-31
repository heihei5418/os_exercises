fin = open("input.txt", 'r')
mem_size = 4

for line in fin:
	visit_mem = line.strip().split()
	num = 0
	pages = []
	for item in visit_mem:
		if item in pages:
			pages.remove(item)
			pages.insert(0, item)
			print("Find page %s" % item)
		elif len(pages) < mem_size:
			pages.insert(0, item)
			print("Insert new page %s" % item)
		else:
			num += 1
			print("Page fault! Remove page %s, insert page %s" % (pages.pop(), item))
			pages.insert(0, item)
	print("Total %d page fault\n" % num)

fin.close()