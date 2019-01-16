function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
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
