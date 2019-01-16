function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isPlayerThere({x = 33190, y = 31629, z = 13}) and Game.isItemThere({x = 33210, y = 31630, z = 13},1295) then 
		Game.removeItemOnMap({x = 33210, y = 31630, z = 13}, 1295)
		Game.removeItemOnMap({x = 33211, y = 31630, z = 13}, 1295)
		Game.removeItemOnMap({x = 33212, y = 31630, z = 13}, 1295)
	end
end

function onStepOut(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isPlayerThere({x = 33190, y = 31629, z = 13}) then 
		doRelocate({x = 33210, y = 31630, z = 13},{x = 33210, y = 31631, z = 13})
		doRelocate({x = 33211, y = 31630, z = 13},{x = 33211, y = 31631, z = 13})
		doRelocate({x = 33212, y = 31630, z = 13},{x = 33212, y = 31631, z = 13})
		Game.createItem(1295, 1, {x = 33210, y = 31630, z = 13})
		Game.createItem(1295, 1, {x = 33211, y = 31630, z = 13})
		Game.createItem(1295, 1, {x = 33212, y = 31630, z = 13})
	end
end
