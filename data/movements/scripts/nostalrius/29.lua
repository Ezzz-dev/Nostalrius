function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isSorcerer() and Game.isItemThere({x = 32679, y = 32089, z = 08}, 3059) then 
		item:transform(430, 1)
		item:decay()
	end
end

function onStepOut(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		item:transform(431, 1)
		item:decay()
		doRelocate({x = 32692, y = 32102, z = 10},{x = 32691, y = 32102, z = 10})
		Game.createItem(1281, 1, {x = 32692, y = 32102, z = 10})
	end
end
