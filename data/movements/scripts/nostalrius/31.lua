function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isPaladin() and Game.isItemThere({x = 32673, y = 32083, z = 08}, 3349) then
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
