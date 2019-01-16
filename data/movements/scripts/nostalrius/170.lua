function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33070, y = 31620, z = 15})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33070, y = 31620, z = 15})
end