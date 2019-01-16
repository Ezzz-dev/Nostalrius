function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isDruid() and Game.isItemThere({x = 32667, y = 32089, z = 08}, 3585) then 
		item:transform(430, 1)
		item:decay()
	end
end

function onStepOut(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		item:transform(431, 1)
		item:decay()
	end
end
