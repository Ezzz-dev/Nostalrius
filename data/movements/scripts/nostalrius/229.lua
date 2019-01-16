function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32767, y = 32229, z = 07})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32767, y = 32229, z = 07})
end
