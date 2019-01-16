function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32874, y = 31953, z = 12})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32874, y = 31953, z = 12})
end