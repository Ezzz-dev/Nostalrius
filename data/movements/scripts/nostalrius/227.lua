function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isDruid() then
		doRelocate(item:getPosition(),{x = 32851, y = 32339, z = 06})
	else
		doRelocate(item:getPosition(),{x = 32836, y = 32294, z = 07}) 
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32836, y = 32294, z = 07}) 
end
