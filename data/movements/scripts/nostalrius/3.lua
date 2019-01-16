function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32771, y = 32297, z = 10},389) then 
		Game.removeItemOnMap({x = 32771, y = 32297, z = 10}, 389)
		Game.transformItemOnMap({x = 32770, y = 32282, z = 10}, 371, 395)
	end
end

function onStepOut(creature, item, position, fromPosition)
	if not Game.isItemThere({x = 32771, y = 32297, z = 10}, 389) and creature:isPlayer() then
		doRelocate({x = 32771, y = 32297, z = 10},{x = 32771, y = 32296, z = 10})
		Game.createItem(389, 1, {x = 32771, y = 32297, z = 10})
		Game.transformItemOnMap({x = 32770, y = 32282, z = 10}, 395, 371)
	end
end
