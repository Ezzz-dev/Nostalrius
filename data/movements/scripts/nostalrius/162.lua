function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isSorcerer() then
		doRelocate(item:getPosition(),{x = 32659, y = 32105, z = 09})
	else
		doRelocate(item:getPosition(),{x = 32641, y = 32141, z = 11})
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32641, y = 32141, z = 11})
end