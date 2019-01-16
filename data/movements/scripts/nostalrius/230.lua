function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isSorcerer() then 
		item:transform(453, 1)
		item:decay()
	end
end

function onStepOut(creature, item, position, fromPosition)
	item:transform(452, 1)
	item:decay()
end